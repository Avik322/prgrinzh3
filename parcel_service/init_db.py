from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from models import Base, Parcel
from sqlalchemy import Index
import os

DATABASE_URL = os.environ.get("DATABASE_URL", "postgresql://postgres:postgres@db:5432/parcels")

engine = create_engine(DATABASE_URL)
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)

def init_db():
    Base.metadata.create_all(bind=engine)

    # —оздание индексов вручную (если не описано в models)
    Index("ix_parcel_sender", Parcel.sender_id).create(bind=engine, checkfirst=True)
    Index("ix_parcel_receiver", Parcel.receiver_id).create(bind=engine, checkfirst=True)

    # ƒобавление тестовых данных
    db = SessionLocal()
    if not db.query(Parcel).first():
        test_parcel_1 = Parcel(sender_id=1, receiver_id=2, status="Created")
        test_parcel_2 = Parcel(sender_id=3, receiver_id=4, status="In Transit")
        db.add_all([test_parcel_1, test_parcel_2])
        db.commit()
    db.close()

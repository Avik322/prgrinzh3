from sqlalchemy import Column, Integer, String, DateTime, ForeignKey, Index
from sqlalchemy.orm import declarative_base
from database import Base

Base = declarative_base()

class Parcel(Base):
    __tablename__ = "parcels"

    id = Column(Integer, primary_key=True, index=True)
    sender_id = Column(Integer, index=True)       # <-- обязательное поле
    receiver_id = Column(Integer, index=True)     # <-- обязательное поле
    status = Column(String, index=True)           # <-- обязательное поле

    __table_args__ = (
        Index("ix_parcel_sender", "sender_id"),
        Index("ix_parcel_receiver", "receiver_id"),
        Index("ix_parcel_status", "status"),
    )
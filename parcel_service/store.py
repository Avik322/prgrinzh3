from database import SessionLocal
from models import Parcel


class ParcelStore:
    def create_parcel(self, sender_id, description):
        db = SessionLocal()
        parcel = Parcel(sender_id=sender_id, description=description)
        db.add(parcel)
        db.commit()
        db.refresh(parcel)
        db.close()
        return parcel

    def get_parcels_by_user(self, user_id):
        db = SessionLocal()
        parcels = db.query(Parcel).filter(Parcel.sender_id == user_id).all()
        db.close()
        return parcels

store = ParcelStore()

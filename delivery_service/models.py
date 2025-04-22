from pydantic import BaseModel

class DeliveryIn(BaseModel):
    sender_id: int
    receiver_id: int
    parcel_id: int

class DeliveryOut(DeliveryIn):
    id: int

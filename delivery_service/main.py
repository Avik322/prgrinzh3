from fastapi import FastAPI, Depends, HTTPException
from fastapi.security import HTTPBearer, HTTPAuthorizationCredentials
from jose import JWTError, jwt

from models import DeliveryIn, DeliveryOut
from store import store

app = FastAPI()

SECRET_KEY = "secret"
ALGORITHM = "HS256"
security = HTTPBearer()

def verify_token(credentials: HTTPAuthorizationCredentials = Depends(security)):
    try:
        payload = jwt.decode(credentials.credentials, SECRET_KEY, algorithms=[ALGORITHM], issuer="auth0")
        return payload["username"]
    except JWTError:
        raise HTTPException(status_code=401, detail="Invalid or expired token")

@app.post("/deliveries", response_model=DeliveryOut)
def create_delivery(delivery: DeliveryIn, user=Depends(verify_token)):
    return store.create_delivery(delivery.sender_id, delivery.receiver_id, delivery.parcel_id)

@app.get("/deliveries/sender/{sender_id}", response_model=list[DeliveryOut])
def deliveries_by_sender(sender_id: int, user=Depends(verify_token)):
    return store.get_by_sender(sender_id)

@app.get("/deliveries/receiver/{receiver_id}", response_model=list[DeliveryOut])
def deliveries_by_receiver(receiver_id: int, user=Depends(verify_token)):
    return store.get_by_receiver(receiver_id)

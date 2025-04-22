from fastapi import FastAPI, Depends, HTTPException, Path
from fastapi.security import HTTPBearer, HTTPAuthorizationCredentials
from jose import jwt, JWTError
from pydantic import BaseModel
import store
import init_db
from database import SessionLocal
from models import Parcel


SECRET_KEY = "secret"
ALGORITHM = "HS256"

app = FastAPI()
security = HTTPBearer()

@app.on_event("startup")
def startup():
    init_db.init_db()

def verify_token(credentials: HTTPAuthorizationCredentials = Depends(security)):
    try:
        payload = jwt.decode(credentials.credentials, SECRET_KEY, algorithms=[ALGORITHM])
        return payload["username"]
    except JWTError:
        raise HTTPException(status_code=401, detail="Invalid or expired token")

class ParcelIn(BaseModel):
    sender_id: int
    description: str

@app.post("/parcels")
def create_parcel(parcel: ParcelIn, username: str = Depends(verify_token)):
    return store.store.create_parcel(parcel.sender_id, parcel.description)

@app.get("/parcels/user/{sender_id}")
def get_parcels_by_user(sender_id: int, username: str = Depends(verify_token)):
    db = SessionLocal()
    parcels = db.query(Parcel).filter(Parcel.sender_id == sender_id).all()
    db.close()
    return parcels

@app.get("/parcels")
def get_all_parcels(username: str = Depends(verify_token)):
    db = SessionLocal()
    parcels = db.query(Parcel).all()
    db.close()
    return parcels

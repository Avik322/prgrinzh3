class InMemoryStore:
    def __init__(self):
        self.deliveries = []
        self.next_id = 1

    def create_delivery(self, sender_id, receiver_id, parcel_id):
        delivery = {
            "id": self.next_id,
            "sender_id": sender_id,
            "receiver_id": receiver_id,
            "parcel_id": parcel_id
        }
        self.deliveries.append(delivery)
        self.next_id += 1
        return delivery

    def get_by_sender(self, sender_id):
        return [d for d in self.deliveries if d["sender_id"] == sender_id]

    def get_by_receiver(self, receiver_id):
        return [d for d in self.deliveries if d["receiver_id"] == receiver_id]

store = InMemoryStore()

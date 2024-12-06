# Message Delivery Status Tracker  

## 📖 Project Description  

This project determines whether messages are delivered or dropped based on timestamps and a delay threshold \(k\). It is useful for scenarios where duplicate or frequent messages need to be filtered.  

### Key Features  
- Evaluates message delivery based on timestamps.
- Drops messages sent within a specified threshold \(k\) seconds of the last delivery.
- Returns a status list for each message (`"true"` for delivered, `"false"` for dropped).

---

## 🛠️ How It Works  

1. **Input**:  
   - A list of timestamps (integers).  
   - A list of messages (strings).  
   - A threshold \(k\) (integer).  

2. **Processing**:  
   - Maintains a record of the last delivery time for each message.  
   - Compares the current timestamp with the last delivery time.  
   - Decides to deliver or drop based on the threshold \(k\).  

3. **Output**:  
   - A list of `"true"` or `"false"` indicating the delivery status of each message.

---

## 🚀 How to Run  

1. Clone this repository:  
   ```bash
   git clone https://github.com/<your-username>/message-delivery-status-tracker.git
   cd message-delivery-status-tracker

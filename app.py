rom flask import Flask, request, jsonify
from flask_cors import CORS
import threading
import time

app = Flask(__name__)


CORS(app)


received_data = {}


def send_data_periodically():
    while True:
        if received_data:
            
            print("Sending received data:", received_data)
        else:
            print("No data received yet.")

        time.sleep(5) 


thread = threading.Thread(target=send_data_periodically)
thread.daemon = True  
thread.start()


@app.route('/data', methods=['POST'])
def receive_data():
    try:
        data = request.get_json()  
        print("Data received:", data)  

        
        global received_data
        received_data = data  

        return jsonify({"status": "success", "message": "Data received"})
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)})


@app.route('/data', methods=['GET'])
def get_data():
    global received_data
    if received_data:
        return jsonify(received_data)
    else:
        return jsonify({"status": "error", "message": "No data received yet"})



@app.route('/')
def home():
    return "Flask API is running!"

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=80)  
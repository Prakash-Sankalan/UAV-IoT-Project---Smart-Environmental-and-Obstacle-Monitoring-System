from flask import Flask, request, jsonify
import requests  

app = Flask(__name__)


AWS_SERVER_URL = "http://3.89.74.81/data"  

@app.route('/data', methods=['POST'])
def receive_and_forward_data():
    try:
        
        data = request.get_json()
        print("Data received from NodeMCU:", data)

        
        aws_response = requests.post(AWS_SERVER_URL, json=data, headers={"Content-Type": "application/json"})

        
        if aws_response.status_code == 200:
            print("Data forwarded to AWS successfully.")
            return jsonify({"status": "success", "message": "Data received and forwarded to AWS"}), 200
        else:
            print("Failed to forward data to AWS. Status Code:", aws_response.status_code)
            return jsonify({"status": "error", "message": "Failed to forward data to AWS"}), 500

    except Exception as e:
        print("Error:", str(e))
        return jsonify({"status": "error", "message": str(e)}), 500


@app.route('/', methods=['GET'])
def home():
    return "Raspberry Pi Flask Server is running and forwarding data to AWS."

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)

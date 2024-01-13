import random 
import requests
import json
import time

class Transformer:
    number_of_transformers = 0

    def __init__(self, devUID: str):
        self.devUID = devUID
        self.output_current = None
        self.output_voltage = None
        self.output_power = None
        self.output_reactive_power = None
        self.output_frequency = None

    def init(self):
        self.output_current = 100
        self.output_voltage = 415
        self.output_power = self.output_current * self.output_voltage
        self.output_reactive_power = 0
        self.output_frequency = 60

    def generateValues(self, upperbound: int, lowerbound: int):
        self.output_current = random.uniform(lowerbound, upperbound + self.output_current)
        self.output_voltage = random.uniform(lowerbound, upperbound + self.output_voltage)
        self.output_power = self.output_current * self.output_voltage
        self.output_reactive_power = random.uniform(lowerbound, upperbound)
        self.output_frequency = random.uniform(lowerbound, 72)

    def transmit(self):
        values = {
            'devUID': self.devUID,
            'output_current': self.output_current,
            'output_voltage': self.output_voltage,
            'output_power': self.output_power,
            'output_reactive_power': self.output_reactive_power,
            'output_frequency': self.output_frequency,
        }
        data = {'data': values}
        print("Data being sent:", values)

        # Ensure the 'Content-Type' header is set to 'application/json'
        headers = {'Content-Type': 'application/json'}

        # Use json parameter to send JSON data
        request = requests.post(url='http://localhost:8000/data/api/', json=data, headers=headers)

        if request.status_code == 200:
            print("Request successful")
        else:
            print("Sending Request Failed")

    def __str__(self):
        return f"Transformer <[devID: {self.devUID}]>"

    @classmethod
    def create_transformer(cls, devUID: str):
        cls.number_of_transformers += 1
        return cls(devUID)


def main():
    # Create 5 transformers
    transformers = [Transformer.create_transformer(str(i + 1)) for i in range(5)]

    for transformer in transformers:
        transformer.init()

    try:
        while True:
            # Generate values periodically
            for transformer in transformers:
                transformer.generateValues(upperbound=100, lowerbound=0)

            # Transmit data to the server
            for transformer in transformers:
                transformer.transmit()
                time.sleep(5)
            # Wait for some time before generating and transmitting again
            time.sleep(10)  # Adjust the sleep duration as needed

    except KeyboardInterrupt:
        print("Simulation terminated by user")

if __name__ == "__main__":
    main()

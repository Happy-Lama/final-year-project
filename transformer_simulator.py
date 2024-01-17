import random 
import requests
import json
import time




class Transformer:
    number_of_transformers = 0

    ACCEPTABLE_VOLTAGE = [220, 240]
    ACCEPTABLE_REACTIVE_POWER = 0.3 #30% of the active power
    ACCEPTABLE_FREQUENCY = [47, 53]

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
        self.output_frequency = 50

    def generateValues(self, deviation, malfunction_probability):
        if random.random() < malfunction_probability:
            self.output_current = random.uniform(self.output_current - deviation, self.output_current + deviation)
            self.output_voltage = random.uniform(self.output_voltage - deviation, self.output_voltage + deviation)
            self.output_power = self.output_current * self.output_voltage
            self.output_reactive_power = random.uniform(0,1) * self.output_power
            self.output_frequency = random.uniform(0, 1) * 50
            print('Transformer malfunctioned')
        else:
            self.output_current = random.uniform(self.output_current - deviation, self.output_current + deviation)
            self.output_voltage = random.uniform(self.ACCEPTABLE_VOLTAGE[0], self.ACCEPTABLE_VOLTAGE[1])
            self.output_power = self.output_current * self.output_voltage
            self.output_reactive_power = random.uniform(0, self.ACCEPTABLE_REACTIVE_POWER) * self.output_power
            self.output_frequency = random.uniform(self.ACCEPTABLE_FREQUENCY[0], self.ACCEPTABLE_FREQUENCY[1])

    def transmit(self, successful_transmission_probability):
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
        if successful_transmission_probability > random.random():
        # Use json parameter to send JSON data
            request = requests.post(url='http://localhost:8000/data/api/', json=data, headers=headers)

            if request.status_code == 200:
                print("Request successful")
            else:
                print("Sending Request Failed")
        else:
            print('Failed to send')

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
                transformer.generateValues(deviation=20, malfunction_probability=0.1)

            # Transmit data to the server
            for transformer in transformers:
                transformer.transmit(successful_transmission_probability=0.8)
                time.sleep(5)
            # Wait for some time before generating and transmitting again
            time.sleep(60)  # Adjust the sleep duration as needed

    except KeyboardInterrupt:
        print("Simulation terminated by user")

if __name__ == "__main__":
    main()


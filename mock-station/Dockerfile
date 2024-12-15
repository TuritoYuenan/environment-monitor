# Use the python image (alpine version for lightweight size)
FROM python:alpine

# Metadata
LABEL org.opencontainers.image.title="Mock Weather Station"
LABEL org.opencontainers.image.authors="turitoyuenan@proton.me"
LABEL org.opencontainers.image.version="latest"
LABEL org.opencontainers.image.description="Publish mock weather data to the MQTT broker"

# Deploy function in /app directory
WORKDIR /app

# Import list of requirements
COPY requirements.txt .

# Install required packages
RUN pip install --no-cache-dir -r requirements.txt

# Import function code
COPY main.py .

# Run the function
CMD [ "python", "main.py" ]

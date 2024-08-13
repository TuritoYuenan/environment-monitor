# Use the python image (alpine version for lightweight size)
FROM python:alpine

# Deploy function in /app directory
WORKDIR /app

# Import function code
COPY . .

# Install required packages
RUN pip install --no-cache-dir -r requirements.txt

# Run the function
CMD [ "python", "main.py" ]

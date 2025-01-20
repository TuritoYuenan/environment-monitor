# build stage
FROM node:lts-alpine AS build-stage
WORKDIR /app
COPY package*.json ./
RUN npm install
COPY . .
RUN npm run build

# production stage
FROM busybox:1.30 AS runner
WORKDIR /app
COPY --from=build-stage /app/dist .
EXPOSE 8080
CMD ["busybox", "httpd", "-f", "-v", "-p", "8080"]

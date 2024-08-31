![Project Banner](./Banner.png)

# Swinburne Weather Service (codename: ZimmerWetter)

This is a university project aiming towards studying, researching and applying Internet-of-Things technology through developing and deploying a weather station system at the campus of Swinburne University of Technology in Ho Chi Minh city, Vietnam.

In short, an IoT Weather Station project.

## How to deploy this? / Manual

### Raspberry Pi Component

1. Prepare a Raspberry Pi 3+ with a static IP address, Git, and Docker Compose
2. Clone this repository
3. Create the file `pwfile` in `config/mosquitto` with 0700 permission
4. Create the file `compose.override.yml` by copying `compose.override.template.yml`
5. Enter required information into `compose.override.yml`
6. In the terminal working at the repository's directory, run `docker compose up -d`

### Weather Station Component

1. Clone this repository
2. Open the `esp32` directory using either **Arduino IDE** or **VSCode with Arduino extension**
3. Copy the file `secrets.template.h` and name it `secrets.h`
4. Enter required information into the `secrets.h` file
5. Connect an ESP32 to your device
6. Flash the Arduino sketch into the ESP32

## What does it measure?

- Temperature (ºC)
- Humidity (%)
- Atmospheric pressure (Pa)
- Rainfall (mm)
- Wind speed (m/s)
- Wind direction (º)

## What technologies are used? / Tech stack

![Technologies used in ZimmerWetter](https://github-readme-tech-stack.vercel.app/api/cards?title=Technologies+used+in+ZimmerWetter&borderRadius=0&lineHeight=5&lineCount=1&width=800&hideTitle=true&line1=html5%2CHTML%2CE34F26%3Bcss3%2CCSS%2C1572b6%3Btypescript%2CTypeScript%2C3178c6%3Bcplusplus%2CC%2B%2B%2C00599c%3Bsvelte%2CSvelteKit%2Cff5800%3Bpostgresql%2CXata%2C9f00ff%3Barduino%2CArduino%2C006dff%3Bespressif%2CESP8266%2CE7352C%3B)

![Architecture Diagram](.github/Diagram.png)

## Who is involved? / Credits

- Author: **Nguyen Ta Minh Triet**, Freshman @ Swinburne University, HCMC, Vietnam
- Co-author: **Nguyen Khanh Phuc Thinh**, Sophomore @ Swinburne University, HCMC, Vietnam
- Member: **Tong Duc Tu Tam**, Freshman @ Swinburne University, HCMC, Vietnam
- Member: **Nguyen Nhat Minh**, Sophomore @ Swinburne University, HCMC, Vietnam
- Member: **Huynh Nguyen Quoc Bao**, Junior @ Swinburne University, HCMC, Vietnam
- Mentor: **Dr. Pham Van Dai**, Lecturer @ Swinburne University, Hanoi, Vietnam
- Manager: **Ms. Titan Vo** @ Swinburne University Academic Department, HCMC, VIetnam

/**
 * Format date. Used for weather reporting
 * @param date Date object
 * @returns
 */
export function formatDate(date: Date) {
	const format = Intl.DateTimeFormat('en-AU', {
		timeStyle: "medium",
		dateStyle: "medium",
		hour12: false,
	});

	return format.format(date);
}

/**
 * Give an arbitrary description of the current weather based on temperature and humidity
 * @param temperature Temperature value in degree Celsius
 * @param humidity Humidity value in %
 * @returns <Word that describes temperature> and <Word that describes humidity>
 */
export function describe(temperature: number, humidity: number): string {
	let description = "";

	// Describe temperature
	// https://loveenglish.org/temperature-vocabulary
	if (temperature < 0) {
		description += "Freezing";
	} else if (temperature < 6) {
		description += "Cold";
	} else if (temperature < 10) {
		description += "Chilly";
	} else if (temperature < 15) {
		description += "Cool";
	} else if (temperature < 30) {
		description += "Warm";
	} else if (temperature < 35) {
		description += "Hot";
	} else {
		description += "Sweltering";
	}

	// Describe humidity
	// https://hvac-boss.com/faq/proper-humidity-for-your-house
	if (humidity < 30) {
		description += " and Dry";
	} else if (humidity < 50) {
		description += " with Normal humidity";
	} else {
		description += " and Humid";
	}

	return description;
}

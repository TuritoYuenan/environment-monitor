import type { PageServerLoad } from './$types';
import { XataClient } from '$lib/xata';

const xata = new XataClient({
	apiKey: import.meta.env.VITE_XATA_API_KEY,
	branch: import.meta.env.VITE_XATA_BRANCH
});

export const load: PageServerLoad = async () => {
	const data = await xata.db.weather_data
		.sort("xata.createdAt", "desc")
		.getFirst();

	// Blunder code 2: Electric boogaloo
	return {
		temperature: data?.temperature!,
		humidity: data?.humidity!,
		pressure: data?.pressure!,
		windSpeedAvg: data?.windSpeedAvg!,
		windSpeedMax: data?.windSpeedMax!,
		windDirection: data?.windDirection!,
		rainfall_D: data?.rainfall_D!,
		rainfall_H: data?.rainfall_H!,
		xata: data?.xata!
	};
}

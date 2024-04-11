<script lang="ts">
	import type { PageServerData } from "./$types";
	import { formatDate, describe } from "$lib/utils";

	export let data: PageServerData;
</script>

<main class="grid">
	<section style:grid-area="ds">
		<h2>
			<img
				src="/icons/report.svg"
				width="40"
				height="40"
				alt="Report"
			/>{formatDate(data.xata.createdAt)} Report
		</h2>
		<p>{describe(data.temperature, data.humidity)}</p>
	</section>
	<section style:grid-area="tp">
		<h2>
			<img
				src="/icons/tempture.svg"
				width="40"
				height="40"
				alt="Temperature"
			/>Temperature
		</h2>
		{#if data.temperature > 125 || data.temperature < -40}
			<p>OVERLOAD</p>
		{:else}
			<p>{data.temperature.toFixed(2)} &deg;C</p>
		{/if}
	</section>
	<section style:grid-area="ht">
		<h2>
			<img
				src="/icons/humidity.svg"
				width="40"
				height="40"
				alt="Humidity"
			/>Humidity
		</h2>
		{#if data.humidity <= 100}
			<p>{data.humidity.toFixed(0)} %</p>
		{:else}
			<p>OVERLOAD</p>
		{/if}
	</section>
	<section style:grid-area="ps">
		<h2>
			<img
				src="/icons/pressure.svg"
				width="40"
				height="40"
				alt="Pressure"
			/>Barometric Pressure
		</h2>
		<p>{data.pressure.toFixed(0)} pascals</p>
	</section>
	<section style:grid-area="rn">
		<h2>
			<img
				src="/icons/rainfall.svg"
				width="40"
				height="40"
				alt="Rainfall"
			/>Rainfall (1 Hour)
		</h2>
		<p>{data.rainfall_H.toFixed(2)} mm</p>
		<h2>
			<img
				src="/icons/rainfall.svg"
				width="40"
				height="40"
				alt="Rainfall"
			/>Rainfall (1 Day)
		</h2>
		<p>{data.rainfall_D.toFixed(2)} mm</p>
	</section>
	<section style:grid-area="wd">
		<h2>
			<img
				src="/icons/wind-spd.svg"
				width="40"
				height="40"
				alt="Wind Speed"
			/>Average Wind Speed
		</h2>
		<p>{data.windSpeedAvg.toFixed(2)} m/s</p>
		<h2>
			<img
				src="/icons/wind-spd.svg"
				width="40"
				height="40"
				alt="Wind Speed"
			/>Maximum Wind Speed
		</h2>
		<p>{data.windSpeedMax.toFixed(2)} m/s</p>
		<h2>
			<img
				src="/icons/wind-dir.svg"
				width="40"
				height="40"
				alt="Wind Direction"
			/>Wind Direction
		</h2>
		{#if data.windDirection < 360}
			<p>{data.windDirection.toFixed(0)} degrees</p>
		{:else}
			<p>OVERLOAD</p>
		{/if}
	</section>
</main>

<style>
	main {
		padding: 1rem;
		grid-template-columns: 1fr 1fr 1fr;
		grid-template-areas: "ds rn wd" "tp ht ps";
	}

	section h2 {
		display: flex;
		align-items: center;
		gap: 0.5rem;
	}

	p {
		font-size: 3rem;
		text-align: end;
	}

	@media (width <= 1100px) {
		main {
			grid-template-columns: 1fr 1fr;
			grid-template-areas: "ds tp" "ps ht" "wd rn";
		}
	}
</style>

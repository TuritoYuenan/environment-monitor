<script lang="ts">
	import fields from "./fields";
	import fluxQuery from "./influx";
	import Card from "./lib/Card.svelte";
	import Metric from "./lib/Metric.svelte";

	const query = `
    from(bucket: "weather_data")
    |> range(start: -5s)
    |> filter(fn: (r) => r._measurement == "weather")
    `;

	let buffer: Array<{ [key: string]: any }> = [];
	let data: typeof buffer = [];
	let temperature: number = NaN;
	let lastUpdated: Date;

	$: {
		fluxQuery(query)
			.then((result) => {
				buffer = result;
				console.table(buffer);
				if (buffer.length > 0) {
					data = buffer.filter((row) => row._field !== "temperature");
					temperature = buffer.find((row) => row._field === "temperature")?._value as number;
					lastUpdated = new Date(buffer[0]._time);
				}
			})
			.catch((error) => {
				console.error("Error fetching data:", error);
			});
	}
</script>

<main>
	<header style:grid-area="h" class="parallax">
		<h1>{fields["temperature"].sanitise(temperature)}&deg;C</h1>
		<p><span class="material-symbols-sharp">weather_mix</span>Warm & Humid</p>
		<p><span class="material-symbols-sharp">location_on</span>Tan Binh, HCMC, Vietnam</p>
	</header>

	<section style:grid-area="m">
		<h2>Overview</h2>
		{#if lastUpdated}
			<em>Last updated {lastUpdated.toLocaleTimeString()}</em>
		{/if}

		<div>
			{#if data.length === 0}
				<Card>
					<p>Receiving the latest weather data...</p>
				</Card>
			{/if}
			{#each data as metric}
				<Card>
					<Metric
						icon={fields[metric._field].icon}
						label={fields[metric._field].label}
						value={fields[metric._field].sanitise(metric._value)}
						unit={fields[metric._field].unit}
					/>
				</Card>
			{/each}
		</div>
	</section>

	<footer style:grid-area="f">
		<p>Swinburne Weather Service. &copy; 2024 Team OrangeCat.</p>
	</footer>
</main>

<style>
	main {
		height: 100vh;
		display: grid;
		grid-template-columns: 35% auto;
		grid-template-rows: 1fr auto;
		grid-template-areas: "h m" "h f";
	}

	.parallax {
		--tint-clr: #1e1e2eaa;
		--tint: linear-gradient(0deg, var(--tint-clr), var(--tint-clr));
		background:
			var(--tint),
			url(/roblox.png) 35% no-repeat;
		background-size: cover;
	}

	header {
		padding: 2rem;
		align-content: center;
	}

	header h1 {
		font-size: 7rem;
	}

	header p {
		font-size: 1.5rem;
	}

	header span.material-symbols-sharp {
		padding-right: 0.8rem;
		font-size: 2em;
		translate: 0 0.3em;
	}

	section {
		padding: 1rem;
		gap: 1rem;
		display: flex;
		flex-direction: column;
		justify-content: center;
		overflow: scroll;
	}

	footer {
		padding: 0.5rem 1rem;
		background-color: var(--ctp-mocha-mantle);
	}

	div {
		margin-block: 1rem;
		display: grid;
		gap: 1rem;
		grid-template-columns: repeat(auto-fit, minmax(300px, 1fr));
	}

	@media (width <= 1000px) {
		main {
			display: block;
		}

		header {
			height: 40vh;
		}
	}
</style>

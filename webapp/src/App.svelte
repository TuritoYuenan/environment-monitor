<script lang="ts">
	import Container from "./lib/Container.svelte";
	import Measure from "./lib/Measure.svelte";
	import { client } from "./influx";

	const query = client.query(
		`SELECT * FROM "weather" ORDER BY time DESC LIMIT 1`,
		'weather_data', { type: 'sql' }
	).return();
</script>

<main>
	<header style:grid-area="header">
		<h1>29&deg;C</h1>
		<p>Warm & Humid</p>
	</header>

	<section style:grid-area="main">
		<h2>Overview</h2>

		<div>
			<Container>
				<Measure icon="airwave" label="Air Pressure" value={101325} unit="Pa" />
			</Container>
			<Container>
				<Measure icon="humidity_percentage" label="Air Humidity" value={100} unit="%" />
			</Container>
			<Container>
				<Measure icon="air" label="Avg. Wind Speed" value={1.5} unit="m/s" />
			</Container>
			<Container>
				<Measure icon="air" label="Max. Wind Speed" value={10.2} unit="m/s" />
			</Container>
			<Container>
				<Measure icon="rainy" label="Hourly Rainfall" value={12} unit="mm" />
			</Container>
			<Container>
				<Measure icon="rainy" label="Daily Rainfall" value={46} unit="mm" />
			</Container>
			<Container>
				<Measure icon="explore" label="Wind Direction" value={90} unit="deg" />
			</Container>
		</div>
	</section>

	<footer style:grid-area="footer">
		<p>Swinburne Weather Service. &copy; 2024 Minh Triet, Phuc Thinh et al.</p>
	</footer>
</main>

<style>
	main {
		height: 100vh;
		display: grid;
		grid-template-columns: 35% auto;
		grid-template-rows: 1fr auto;
		grid-template-areas: 'header main' 'footer footer';
	}

	header {
		--tint-clr: #1e1e2e70;
		--tint: linear-gradient(0deg, var(--tint-clr), var(--tint-clr));
		padding: 1rem;
		align-content: center;
		background: var(--tint), url(/roblox.png) 35% no-repeat;
		background-size: cover;
		text-align: center;
	}

	header h1 {
		font-size: 5rem;
	}

	header p {
		font-size: 2rem;
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
	}

	div {
		margin-block: 1rem;
		display: grid;
		gap: 1rem;
		grid-template-columns: repeat(auto-fit, minmax(300px, 1fr));
	}

	@media (width <= 1000px) {
		main {
			grid-template-columns: 1fr;
		}

		header {
			height: 40vh;
		}

		section {
			overflow: unset;
		}
	}
</style>

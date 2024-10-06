<script lang="ts">
	import Container from "./lib/Container.svelte";
	import Measure from "./lib/Measure.svelte";

	let windDirection: number = 0;

	// Simulate dynamic change
	setInterval(() => {
		windDirection = Math.round(Math.random() * 360);
	}, 3000);
</script>

<main>
	<header>
		<h1>29&deg;C</h1>
		<p>Warm & Humid</p>
	</header>
	<section>
		<Container>
			<Measure icon="humidity_percentage" label="Air Humidity" value={100} unit="percent" />
			<Measure icon="airwave" label="Air Pressure" value={101325} unit="pascals" />
		</Container>
		<Container>
			<Measure icon="explore" label="Wind Direction" value={windDirection} unit="deg" />
		</Container>
		<Container>
			<Measure icon="air" label="Wind Speed" />
			<Measure label="Average" value={1.5} unit="m/s" />
			<Measure label="Maximum" value={10.2} unit="m/s" />
		</Container>
		<Container>
			<Measure icon="rainy" label="Rainfall" />
			<Measure label="Hourly" value={12} unit="mm" />
			<Measure label="Daily" value={46} unit="mm" />
		</Container>
		<Container>
			<footer>
				Swinburne Weather Service. &copy; 2024 Minh Triet et al.
			</footer>
		</Container>
	</section>
</main>

<style>
	main {
		height: 100vh;
		display: grid;
		grid-template-columns: 1fr 1fr;
	}

	header {
		--tint-clr: #18192680;
		--tint: linear-gradient(0deg, var(--tint-clr), var(--tint-clr));
		display: flex;
		flex-direction: column;
		align-items: center;
		justify-content: center;
		color: var(--ctp-latte-crust);
		background: var(--tint), url(/background.jpeg);
		background-size: cover;
		background-position: center;
		background-repeat: no-repeat;
		font-weight: bold;
	}

	header h1 {
		font-size: 7rem;
	}

	header p {
		font-size: 3rem;
	}

	section {
		padding: 1rem;
		gap: 1rem;
		display: flex;
		flex-direction: column;
		overflow: scroll;
	}
</style>

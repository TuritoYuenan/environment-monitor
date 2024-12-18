<script lang="ts">
	import { fields, queryExample } from "./influx";
	import Container from "./lib/Container.svelte";
	import Measure from "./lib/Measure.svelte";

	const query = `
    from(bucket: "weather_data")
    |> range(start: -5s)
    |> filter(fn: (r) => r._measurement == "weather")
	|> filter(fn: (r) => r._field != "temperature")
    |> yield(name: "_results")
    `;

	let data: { [key: string]: any }[] = [];

	$: {
		queryExample(query)
			.then((result) => {
				data = result;
				console.log(data);
			})
			.catch((error) => {
				console.error("Error fetching data:", error);
			});
	}
</script>

<main>
	<header style:grid-area="header" class="parallax">
		<h1>29&deg;C</h1>
		<p>Warm & Humid</p>
	</header>

	<section style:grid-area="main">
		<h2>Overview</h2>

		<div>
			{#each data as measurement}
				<Container>
					<Measure
						icon={fields[measurement._field].icon}
						label={fields[measurement._field].label}
						value={fields[measurement._field].sanitise(measurement._value)}
						unit={fields[measurement._field].unit}
					/>
				</Container>
			{/each}
		</div>
	</section>

	<footer style:grid-area="footer">
		<p>Swinburne Weather Service. &copy; 2024 Team OrangeCat.</p>
	</footer>
</main>

<style>
	main {
		height: 100vh;
		display: grid;
		grid-template-columns: 35% auto;
		grid-template-rows: 1fr auto;
		grid-template-areas: "header main" "header footer";
	}

	.parallax {
		--tint-clr: #1e1e2e70;
		--tint: linear-gradient(0deg, var(--tint-clr), var(--tint-clr));
		background:
			var(--tint),
			url(/roblox.png) 35% no-repeat;
		background-size: cover;
	}

	header {
		padding: 1rem;
		align-content: center;
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

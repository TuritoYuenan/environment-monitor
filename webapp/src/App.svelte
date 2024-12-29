<script lang="ts">
	import fields from "./fields";
	import fluxQuery, { query } from "./influx";
	import Overview from "./lib/Overview.svelte";
	import Tabs from "./lib/Tabs.svelte";

	let currentTab = "overview";

	let buffer: Array<{ [key: string]: any }> = [];
	let data: typeof buffer = [];

	let temperature: number = NaN;

	$: {
		fluxQuery(query)
			.then((result) => {
				buffer = result;
				console.table(buffer);
				if (buffer.length > 0) {
					data = buffer.filter((row) => row._field !== "temperature");
					temperature = buffer.find((row) => row._field === "temperature")?._value as number;
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
		<p>
			<span class="material-symbols-sharp">weather_mix</span>Warm & Humid
		</p>
		<p>
			<span class="material-symbols-sharp">location_on</span>Tan Binh,
			HCMC, Vietnam
		</p>
	</header>

	<Tabs bind:currentTab />

	<section style:grid-area="m">

		{#if currentTab === "overview"}
			<Overview {data} />
		{/if}

		{#if currentTab === "timeline"}
			<h2>Timeline</h2>
		{/if}

		{#if currentTab === "settings"}
			<h2>Settings</h2>
		{/if}
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
		grid-template-rows: auto 1fr auto;
		grid-template-areas: "h t" "h m" "h f";
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

	@media (width <= 1000px) {
		main {
			display: block;
		}

		header {
			height: 30vh;
		}

		header h1 {
			font-size: 5rem;
		}

		header p {
			font-size: 1.2rem;
		}
	}
</style>

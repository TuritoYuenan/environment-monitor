<script lang="ts">
	import fields from "../fields";
	import Card from "./Card.svelte";
	import Metric from "./Metric.svelte";

	export let data: Array<{ [key: string]: any }> = [];
	$: lastUpdated = new Date(data[0]?._time);
</script>

<div id="overview">
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

{#if lastUpdated}
	<em>Last updated {lastUpdated.toLocaleTimeString()}</em>
{/if}

<style>
	#overview {
		margin-block: 1rem;
		display: grid;
		gap: 1rem;
		grid-template-columns: repeat(auto-fit, minmax(255px, 1fr));
	}
</style>

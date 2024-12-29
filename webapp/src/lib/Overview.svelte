<script lang="ts">
	import fields from "../fields";
	import Card from "./Card.svelte";
	import Metric from "./Metric.svelte";

	export let data: Array<{ [key: string]: any }> = [];
	$: lastUpdated = new Date(data[0]?._time);
</script>

<div id="overview">
	{#each data as metric}
		<Card>
			<Metric
				icon={fields[metric._field].icon}
				label={fields[metric._field].label}
				value={fields[metric._field].format(metric._value)}
			/>
		</Card>
	{:else}
		<Card>
			<p>Receiving the latest weather data...</p>
		</Card>
	{/each}
</div>

{#if lastUpdated}
	<em>Last updated {lastUpdated.toLocaleTimeString()}</em>
{/if}

<style>
	#overview {
		display: grid;
		gap: 1rem;
		grid-template-columns: repeat(auto-fit, minmax(255px, 1fr));
	}
</style>

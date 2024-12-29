<script lang="ts">
	import Card from "./Card.svelte";

	export let settings: Record<string, any>;
</script>

<Card>
	<p>Temperature unit</p>
	<select name="temp" id="temp" bind:value={settings.tempUnit}>
		<option value="celsius">&deg;C</option>
		<option value="fahrenheit">&deg;F</option>
		<option value="kelvin">K</option>
	</select>
</Card>

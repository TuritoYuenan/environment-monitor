<script lang="ts">
	export let icon: string = '';
	export let label: string;
	export let value: number | false = false;
	export let unit: string = '';
</script>

<div style:text-align={icon ? 'left' : 'right'}>
	<span class="material-symbols-sharp">{icon ? icon : ''}</span>
	<hgroup>
		<h2>{label}</h2>
		{#if value != false}
			<p>{value} {unit}</p>
		{/if}
	</hgroup>
</div>

<style>
	div {
		display: flex;
		gap: 1rem;
		align-items: center;
	}

	div span {
		font-size: 3em;
	}

	div p {
		font-size: 1.6em;
	}
</style>

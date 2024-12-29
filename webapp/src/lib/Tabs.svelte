<script lang="ts">
	export let currentTab = "overview";
	export let tabs = [
		{ name: "overview", label: "Overview" },
		{ name: "timeline", label: "Timeline" },
		{ name: "settings", label: "Settings" },
	];
</script>

<nav style:grid-area="t">
	{#each tabs as tab}
		<button
			class={currentTab === tab.name ? "active" : ""}
			on:click={() => (currentTab = tab.name)}
		>
			{tab.label}
		</button>
	{/each}
</nav>

<style>
	nav {
		padding: 1rem;
		display: flex;
		gap: 0.5rem;
		justify-content: center;
		text-align: center;
	}

	nav button {
		padding: 0.5rem 3rem;
		background-color: var(--ctp-mocha-surface0);
		border-radius: 1rem;

		/* Undo browser default */
		border: none;
		font: inherit;
		color: inherit;
		cursor: pointer;
	}

	nav button.active {
		color: var(--ctp-mocha-base);
		background-color: var(--ctp-mocha-red);
	}
</style>

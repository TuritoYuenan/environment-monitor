<script lang="ts">
	export let currentTab = "overview";
	export let tabs: { name: string; label: string }[];
</script>

<nav style:grid-area="t">
	{#each tabs as tab}
		<button
			class={currentTab === tab.name ? "active shadow" : "shadow"}
			on:click={() => (currentTab = tab.name)}
		>
			{tab.label}
		</button>
	{/each}
</nav>

<style>
	nav {
		display: flex;
		gap: 0.5rem;
		justify-content: center;
		text-align: center;
	}

	nav button {
		width: clamp(6.5rem, 10vw, 10rem);
		padding: 0.5rem 1rem;
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

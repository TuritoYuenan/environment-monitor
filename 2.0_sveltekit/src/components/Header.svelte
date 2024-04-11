<header>
	<div><img src="/swinburne.svg" alt="Swinburne University Logo" /></div>
	<div id="title">
		<h1>Swinburne Weather Service</h1>
		<h2>Weather at Swinburne HCMC, measured by the SEN0186 Station</h2>
	</div>
</header>

<style>
	header {
		padding-block: 1rem;
		background-color: var(--swinburne-offwhite);
		gap: 1rem;
		display: flex;
		flex-wrap: wrap;
		justify-content: center;
		align-items: center;
	}

	img {
		width: auto;
		height: 9rem;
		margin: auto;
		padding-inline: 1rem;
		display: block;
	}

	#title {
		padding: 1rem;
		display: grid;
		align-content: center;
		text-align: center;
	}

	#title > * {
		margin-block: 0.5rem;
	}

	@media (width <= 900px) {
		img {
			height: 6rem;
		}
	}
</style>

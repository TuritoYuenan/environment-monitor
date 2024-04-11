<script lang="ts">
	import "../app.css";
	import Header from "$components/Header.svelte";
	import Footer from "$components/Footer.svelte";
</script>

<svelte:head>
	<title>ZimmerWetter</title>
</svelte:head>

<Header />

<slot />

<Footer />

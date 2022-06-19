<script>
    import { page } from '$app/stores';
    import { onMount } from 'svelte';

    console.log($page.url.pathname);
            
</script>

<div class="header">
    <img src="./title.png" class="logo" alt="logo"/>

    <hr size="1" width="60%" color="#EEEEEE">

    <ul class="nav">
        <li> <a href="humidity" style="{$page.url.pathname === '/humidity' ? 'color: #fb8122;' : ''}">Humidity</a> </li>
        <li>|</li>
        <li> <a href="temperature" style="{$page.url.pathname === '/temperature' ? 'color: #fb8122;' : ''}">Temperature </a> </li>
        <li>|</li>
        <li> <a href="frequency" style="{$page.url.pathname === '/frequency' ? 'color: #fb8122;' : ''}">Frequency</a> </li>
        <li>|</li>
        <li> <a href="level" style="{$page.url.pathname === '/level' ? 'color: #fb8122;' : ''}">Level </a> </li>

    </ul>
</div>

<style>
    .header {
        display: flex;
        flex-direction: column;
        justify-content: center;
        align-items: center;
    }

    .logo {
        margin-top: 20px;
        margin-bottom: 5px;
        width: 200px;
    }

    .nav {
        display: flex;
        justify-content: space-evenly;
        justify-items: center;
        margin-right: 5px;
        margin-left: 5px;
        margin-bottom: 0px;
        list-style-type: none;
    }

    li {
        margin-left: 20px;
        margin-right: 20px;
        color: #EEEEEE;
    }

    a:visited {
        color: #EEEEEE;
        text-decoration: none;
    }

    a:link {
        color: #EEEEEE;
        text-decoration: none;
    }
</style>
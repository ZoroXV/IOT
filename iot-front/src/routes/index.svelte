<script>
      import { onMount } from 'svelte';
      import Header from '$lib/Header.svelte';
      import Footer from '$lib/Footer.svelte';
      import Graph from  '$lib/Graph.svelte';
      import Doughnut from '$lib/Doughnut.svelte';

      import Chart from 'chart.js/auto/auto.js';

      let childGraph;
      let childDoughnut;

      function TurnOnLed() {
          fetch('http://localhost:5000/', {
            method: 'POST',
            headers: {
              Accept: 'application/json',
            }
          }).then();
      }

      function sleep(ms) {
        return new Promise(resolve => setTimeout(resolve, ms));
      }

      async function updateCharts() {
        while (1) {
            if (childGraph == undefined || childDoughnut == undefined) {
                await sleep(1000);
                continue;
            }

            var res = await fetch("http://localhost:5000/", {
                method: 'GET',
                headers: {
                    Accept: 'application/json',
                },
            }).then(res => res.json()); 

            childGraph.updateValue(res.temperature);
            childDoughnut.updateValue(res.humidity);
            await sleep(2000);
        }
      }

      updateCharts();
</script>

<div class="main_div">
    <div class="header"> 
        <Header/>
    </div>

    <div class="graph_box">
        <div class="graph">
            <Doughnut bind:this={childDoughnut}/>
        </div>

        <div class="graph">
            <Graph bind:this={childGraph} minValue={0} maxValue={100} />
        </div>
    </div>

    <div class="turn_on_box">
        <button on:click="{TurnOnLed}">turn on led</button>
    </div>

    <div class="footer">
        <Footer/>
    </div>
</div>

<style>
    .main_div {
        position: absolute;
        top: 0px;
        bottom: 0px;
        right: 0px;
        left: 0px;
        background-color: red;
        height: 100%;

        display: flex;
        flex-direction: column;
    }

    .header {
        background-color : blue;     
        flex-grow: 1;
    }

    .graph_box {
        flex-grow: 12;

        display: flex;
        flex-direction: row;
        justify-content: center;

        background-color : yellow;
    }

    .turn_on_box {
        background-color : green;
        flex-grow: 2;
    }

    .footer {
        flex-grow: 2;
    }

    .graph {
        max-width: 400px;
        max-height: 400px;
        background-color: white;
    }
</style>
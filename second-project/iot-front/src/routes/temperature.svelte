<script>
    import Graph from  '$lib/Graph.svelte';
    import Doughnut from '$lib/Doughnut.svelte';

    import Chart from 'chart.js/auto/auto.js';
    import { getTemperature } from '$lib/store.js';

    let childGraph;
    let curTemp = 20;

    function sleep(ms) {
      return new Promise(resolve => setTimeout(resolve, ms));
    }

    async function updateCharts() {
      while (1) {
          if (childGraph == undefined) {
              await sleep(1000);
              continue;
          }

          var temperature = await getTemperature();

          childGraph.updateValue(temperature);
          curTemp = Math.floor(temperature);

          await sleep(4000);
      }
    }

    updateCharts();
</script>

<div class="container">
    <div class="graph">
        <Graph bind:this={childGraph} minValue={0} maxValue={60} />
        <div class="temperatureContainer">
            <p class="temperature">{curTemp}</p>
            <p class="unit">°C</p>
        </div>
    </div>
</div>

<style>
    .container {
        display: flex;
        flex-direction: column;
        align-items: center;
        width: 100%;
    }


    .graph {
        max-width: 900px;
        max-height: 400px;
        width: 100%;
        height: 100%;
        margin-top: 80px;

    }

    .temperatureContainer {
        display: flex;
        flex-direction: row;
        justify-content: center;
        width: 100%;
    }

    p {
        font-size: 40px;
    }
    .temperature {
        color: #fb8122;
        margin-right: 10px;
        margin-left: 10px;
    }

    .unit {
        color: #EEEEEE;
    }
</style>

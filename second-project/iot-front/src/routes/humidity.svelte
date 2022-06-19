<script>
    import Graph from  '$lib/Graph.svelte';
    import Doughnut from '$lib/Doughnut.svelte';

    import Chart from 'chart.js/auto/auto.js';
    import { getHumidity } from './../lib/store.js';

    let childGraph;
    let childDoughnut;

    function sleep(ms) {
      return new Promise(resolve => setTimeout(resolve, ms));
    }

    async function updateCharts() {
      while (1) {
          if (childGraph == undefined || childDoughnut == undefined) {
              await sleep(1000);
              continue;
          }

          var humidity = await getHumidity();

          childGraph.updateValue(humidity);
          childDoughnut.updateValue(humidity);
          await sleep(4000);
      }
    }

    updateCharts();
</script>

<div class="container">
    <div class="doughnut">
        <Doughnut bind:this={childDoughnut}/>
    </div>

    <div class="graph">
        <Graph bind:this={childGraph} minValue={0} maxValue={100} />
    </div>
</div>

<style>
    .container {
        display: flex;
        width: 100%;
        height: 100%;
        justify-content: center;
        margin-top: 80px;
    }

    .doughnut {
        max-width: 300px;
        max-height: 100px;
        flex-grow: 4;
    }

    .graph {
        max-width: 700px;
        max-height: 400px;
        flex-grow: 10;
    }
</style>

<script>
      import { onMount } from 'svelte';
      import Chart from 'chart.js/auto/auto.js';

      function TurnOnLed() {
          console.log("Turn on led");
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

      async function updateCharts(tempChart, humChart) {
        while (1) {
            await sleep(1000);
            var res = await fetch("http://localhost:5000/", {
                method: 'GET',
                headers: {
                    Accept: 'application/json',
                },
            }).then(res => res.json()); 

            tempChart.data.labels.push(res.time);
            tempChart.data.datasets.forEach((dataset) => {
                dataset.data.push(res.temperature);
            });

            humChart.data.labels.push(res.time);
            humChart.data.datasets.forEach((dataset) => {
                dataset.data[0] = res.humidity;
                dataset.data[1] = 100.0 - res.humidity;
            });

            tempChart.update();
            humChart.update();
        }
      }

      let temperaturePortfolio;
      let humidityPortfolio;

      var temperatureData = {
            labels: [],
            datasets: [
                {
                    label: 'Dataset',
                    data: [],
                    borderColor: "#00FF00",
                    backgroundColor: "#00FFFF"
                }
            ]
        };
        var temperatureConfig = {
            type: 'line',
            data: temperatureData,
            options: {
                responsive: true,
                maintainAspectRatio: false,
                plugins: {
                    legend: {
                        display: false
                    },
                    title: {
                        display: true,
                        text: 'Temperature'
                    }
                }
            }
        };

      var humidityData = {
            labels: [],
            datasets: [
                {
                    label: '',
                    data: [50, 50],
                    backgroundColor: [
                        'rgb(255, 255, 255)',
                        'rgb(0, 255, 0)'
                    ],
                    borderColor: [ "#FFFFFF", "#00FF00" ],
                }
            ]
        };
        var humidityConfig = {
            type: 'doughnut',
            data: humidityData,
            options: {
                responsive: true,
                maintainAspectRatio: false,
                plugins: {
                    legend: {
                        display: false
                    },
                    title: {
                        display: true,
                        text: 'Humidity'
                    }
                }
            }
        };

      onMount(async () => {
        const temperatureCtx = temperaturePortfolio.getContext('2d');
        const humidityCtx = humidityPortfolio.getContext('2d');

        // Initialize chart using default config set
        var temperatureChart = new Chart(temperatureCtx, temperatureConfig);
        var humidityChart = new Chart(humidityCtx, humidityConfig);

        await updateCharts(temperatureChart, humidityChart);
      })

</script>

<div class="main_div">
    <div class="header"> 
        My small thermometer
    </div>

    <div class="graph_box">
        <canvas bind:this={humidityPortfolio} class="graph"/>
        <canvas bind:this={temperaturePortfolio} class="graph"/>
    </div>

    <div class="turn_on_box">
        <button on:click="{TurnOnLed}">turn on led</button>
    </div>

    <div class="footer">
        Made by Jean Sainctavit and Victor le-corre
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
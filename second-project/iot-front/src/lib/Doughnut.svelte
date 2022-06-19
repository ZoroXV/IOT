<script>
    import { onMount } from 'svelte';
    import Chart from 'chart.js/auto/auto.js';

    let portfolio;
    let chart;
    let temp = 20;

    export function updateValue(newValue) {
        temp = Math.floor(newValue);
        chart.data.labels.push(0);
        chart.data.datasets.forEach((dataset) => {
            dataset.data[0] = (100 - temp);
            dataset.data[1] = temp;
        });
        chart.update();
    }

    var data = {
        labels: [],
        datasets: [
            {
                label: '',
                data: [50, 50],
                borderColor: [ "#FFFFFF00", "#fb8122" ],
                backgroundColor: [ "#FFFFFF00", "#fb8122" ]
            }
        ]
    };

    var config = {
        type: 'doughnut',
        data: data,
        options: {
            responsive: true,
            maintainAspectRatio: false,
            plugins: {
                legend: {
                    display: false
                },
                title: {
                    display: false
                }
            }
        }
    };

    onMount(async () => {
        const ctx = portfolio.getContext('2d');

        // Initialize chart using default config set
        chart = new Chart(ctx, config);
    })
</script>

<div class="container">
    <div class="padding">
    </div>

    <div>
        <canvas bind:this={portfolio} class="graph"/>
    </div>

    <div class="text">
        <p class="temperature">{temp}</p>
        <p class="unit"> %</p>
    </div>
</div>

<style>
    .padding {
        height: 70px;
    }

    .container {
        display: flex;
        flex-direction: column;
        align-items: center;
    }

    .graph {
        max-height: 200px;
    }

    .text {
        display: flex;
        align-items: flex-end;
        color: #EEEEEE;
    }

    .temperature {
        color: #fb8122;
        font-size: 40px;
        margin-right: 10px;
    }

    .unit {
        color: #EEEEEE;
        font-size: 40px;
    }
</style>
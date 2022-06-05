<script>
    import { onMount } from 'svelte';
    import Chart from 'chart.js/auto/auto.js';
import { dataset_dev } from 'svelte/internal';

    export let minValue;
    export let maxValue;

    let portfolio;
    let chart;
    let i = 0;

    export function updateValue(newValue) {

        if (i < 10) {
            // chart.data.labels.push(0);
            chart.data.datasets.forEach((dataset) => {
                dataset.data[i] = newValue;
            });
        } else {
            chart.data.datasets.forEach((dataset) => {
                dataset.data.shift();
                dataset.data.push(newValue);
            });
        }
        i++;

        chart.update();
    }

    var data = {
        labels: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9],
        datasets: [
            {
                label: 'Dataset',
                data: [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                fill: true,
                backgroundColor: "rgba(251,129,34,0.2)",
                borderColor: "rgba(251, 129, 34, 1)"
            }
        ]
    };

    var config = {
        type: 'line',
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
            },
            scales: {
                x: {
                    grid: {
                        color: "#00000000"
                    },
                    ticks: {
                        color: "#00000000"
                    }
                },
                y: {
                    min: minValue,
                    max: maxValue,
                    grid: {
                        color: "#EEEEEE33"
                    },
                    ticks: {
                        color: "#EEEEEE"
                    }
                }
            },
        }
    };

    onMount(async () => {
        const ctx = portfolio.getContext('2d');

        // Initialize chart using default config set
        chart = new Chart(ctx, config);
    })
</script>

<canvas bind:this={portfolio} class="graph"/>
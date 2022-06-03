<script>
    import { onMount } from 'svelte';
    import Chart from 'chart.js/auto/auto.js';

    export let minValue;
    export let maxValue;

    let portfolio;
    let chart;

    export function updateValue(newValue) {
        chart.data.labels.push(0);
        chart.data.datasets.forEach((dataset) => {
            dataset.data.push(newValue);
        });
        chart.update();
    }

    var data = {
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
                    display: true,
                    text: 'Temperature'
                }
            },
            scales: {
                y: {
                    min: minValue,
                    max: maxValue
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

<canvas bind:this={portfolio} class="graph"/>
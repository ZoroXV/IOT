<script>
    import { onMount } from 'svelte';
    import Chart from 'chart.js/auto/auto.js';

    let portfolio;
    let chart;

    export function updateValue(newValue) {
        chart.data.labels.push(0);
        chart.data.datasets.forEach((dataset) => {
            dataset.data[0] = newValue;
            dataset.data[1] = 100.0 - newValue;
        });
        chart.update();
    }

    var data = {
        labels: [],
        datasets: [
            {
                label: '',
                data: [50, 50],
                borderColor: [ "#FFFFFF", "#00FF00" ],
                backgroundColor: [ "#FFFFFF", "#00FF00" ]
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
                    display: true,
                    text: 'Temperature'
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
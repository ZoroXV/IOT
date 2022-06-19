var url = "http://107.191.47.167:5001/";
var frequency = 0;

export async function getTemperature() {
    var res = await fetch(url + "stats", {
        method: 'GET',
        headers: {
            Accept: 'application/json',
        },
    }).then(res => res.json()); 

    if (res != null) {
        return res.temperature;
    } else {
        return 0;
    }
}

export async function getHumidity() {
    var res = await fetch(url + "stats", {
        method: 'GET',
        headers: {
            Accept: 'application/json',
        },
    }).then(res => res.json()); 

    if (res != null) {
        return res.humidity;
    } else {
        return 0;
    }
}

export async function getLevel() {
    var res = await fetch(url + "stats", {
        method: 'GET',
        headers: {
            Accept: 'application/json',
        },
    }).then(res => res.json()); 
    
    if (res != null) {
        return res.level;
    } else {
        return 0;
    }
}

export async function setFrequency(freq) {
    frequency = freq;

    // Post the frequency
}

export async function getFrequency() {
    return frequency;
}
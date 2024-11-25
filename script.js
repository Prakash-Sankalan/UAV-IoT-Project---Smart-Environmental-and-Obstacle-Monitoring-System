// Initialize the charts
const tempCtx = document.getElementById('tempChart').getContext('2d');
const humidityCtx = document.getElementById('humidityChart').getContext('2d');
const distanceCtx = document.getElementById('distanceChart').getContext('2d');
const angleCtx = document.getElementById('angleChart').getContext('2d');


// Temperature Chart
const tempChart = new Chart(tempCtx, {
  type: 'line',
  data: {
    labels: [],  // Time labels (can be timestamps or incremental values)
    datasets: [{
      label: 'Temperature (°C)',
      data: [],  // Temperature data will be added here
      borderColor: 'rgba(255, 99, 132, 1)',
      backgroundColor: 'rgba(255, 99, 132, 0.2)',
      fill: false,
      tension: 0.1
    }]
  },
  options: {
    scales: {
      x: {
        title: {
          display: true,
          text: 'Time'
        }
      },
      y: {
        title: {
          display: true,
          text: 'Temperature (°C)'
        },
        beginAtZero: true
      }
    }
  }
});

// Humidity Chart
const humidityChart = new Chart(humidityCtx, {
  type: 'line',
  data: {
    labels: [],  // Time labels (can be timestamps or incremental values)
    datasets: [{
      label: 'Humidity (%)',
      data: [],  // Humidity data will be added here
      borderColor: 'rgba(54, 162, 235, 1)',
      backgroundColor: 'rgba(54, 162, 235, 0.2)',
      fill: false,
      tension: 0.1
    }]
  },
  options: {
    scales: {
      x: {
        title: {
          display: true,
          text: 'Time'
        }
      },
      y: {
        title: {
          display: true,
          text: 'Humidity (%)'
        },
        beginAtZero: true
      }
    }
  }
});

// Distance Chart
const distanceChart = new Chart(distanceCtx, {
  type: 'line',
  data: {
    labels: [],  // Time labels (can be timestamps or incremental values)
    datasets: [{
      label: 'Distance (cm)',
      data: [],  // Distance data will be added here
      borderColor: 'rgba(75, 192, 192, 1)',
      backgroundColor: 'rgba(75, 192, 192, 0.2)',
      fill: false,
      tension: 0.1
    }]
  },
  options: {
    scales: {
      x: {
        title: {
          display: true,
          text: 'Time'
        }
      },
      y: {
        title: {
          display: true,
          text: 'Distance (cm)'
        },
        beginAtZero: true
      }
    }
  }
});

// Angle Chart
const angleChart = new Chart(angleCtx, {
  type: 'line',
  data: {
    labels: [],  // Time labels (can be timestamps or incremental values)
    datasets: [{
      label: 'Angle (°)',
      data: [],  // Angle data will be added here
      borderColor: 'rgba(153, 102, 255, 1)',
      backgroundColor: 'rgba(153, 102, 255, 0.2)',
      fill: false,
      tension: 0.1
    }]
  },
  options: {
    scales: {
      x: {
        title: {
          display: true,
          text: 'Time'
        }
      },
      y: {
        title: {
          display: true,
          text: 'Angle (°)'
        },
        beginAtZero: true
      }
    }
  }
});

// Function to fetch data from the Flask API
// Function to fetch data from the Flask API
async function fetchData() {
  try {
    // Fetch data from the Flask API
    const response = await fetch('http://3.89.74.81/data');
    
    // Check if the response is okay (status code 200)
    if (!response.ok) {
      throw new Error(`HTTP error! Status: ${response.status}`);
    }

    // Parse the JSON response
    const data = await response.json();
    console.log('API Response:', data);  // Log the full API response for inspection

    // Check if the required data is available
    const temperature = data.temperature !== undefined ? data.temperature : 'N/A';
    const humidity = data.humidity !== undefined ? data.humidity : 'N/A';
    const distance = data.distance !== undefined ? data.distance : 'N/A';
    const angle = data.angle !== undefined ? data.angle : 'N/A';
    const intensity = data.intensity !== undefined ? data.intensity : null; // Set to null if undefined

    console.log('Intensity:', intensity);  // Log intensity for debugging

    // Update the dashboard with the latest data
    document.getElementById('usersCount').textContent = `Temperature: ${temperature}°C`;
    document.getElementById('pagesCount').textContent = `Humidity: ${humidity}%`;
    document.getElementById('sessionsCount').textContent = `Distance: ${distance} cm`;
    document.getElementById('bounceRate').textContent = `Angle: ${angle}°`;

    // Only update the illumination status once
    const illuminationStatus = intensity < 50 ? "No illumination" : "Illuminated";
    document.getElementById('illuRate').textContent = illuminationStatus;

    // Get the current time for labels
    const currentTime = new Date().toLocaleTimeString();

    // Update Temperature Chart
    tempChart.data.labels.push(currentTime);
    tempChart.data.datasets[0].data.push(temperature);

    // Update Humidity Chart
    humidityChart.data.labels.push(currentTime);
    humidityChart.data.datasets[0].data.push(humidity);

    // Update Distance Chart
    distanceChart.data.labels.push(currentTime);
    distanceChart.data.datasets[0].data.push(distance);

    // Update Angle Chart
    angleChart.data.labels.push(currentTime);
    angleChart.data.datasets[0].data.push(angle);

    // Remove the first data point if we exceed the limit (keeping the chart clean)
    const maxDataPoints = 10;
    [tempChart, humidityChart, distanceChart, angleChart].forEach((chart) => {
      if (chart.data.labels.length > maxDataPoints) {
        chart.data.labels.shift();
        chart.data.datasets[0].data.shift();
      }
      chart.update(); // Refresh the chart
    });

  } catch (error) {
    console.error('Error fetching data:', error);
    
    // Update the dashboard with error messages
    document.getElementById('usersCount').textContent = 'Error loading data';
    document.getElementById('pagesCount').textContent = 'Error loading data';
    document.getElementById('sessionsCount').textContent = 'Error loading data';
    document.getElementById('bounceRate').textContent = 'Error loading data';
    document.getElementById('illuRate').textContent = 'Error loading data';
  }
}

// Fetch data on page load and refresh every 5 seconds
window.onload = function() {
  // Fetch data when the page loads
  fetchData();

  // Set interval to fetch data every 5 seconds
  setInterval(fetchData, 5000);
};

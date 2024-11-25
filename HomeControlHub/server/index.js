const express = require('express');
const bodyParser = require('body-parser');
const cors = require('cors');

const app = express();
const PORT = 8080;

app.use(cors());
app.use(bodyParser.json());

let bulbStatus = false; // Default status: OFF

app.post('/bulb', (req, res) => {
    const { bulbOn } = req.body;
    console.log(`Bulb status: ${bulbOn ? 'ON' : 'OFF'}`);
    bulbStatus = bulbOn; // Update bulb status
    res.status(200).json({ message: 'Bulb status updated successfully' });
});

// Endpoint to retrieve bulb status via GET
app.get('/bulb', (req, res) => {
    res.status(200).json({ bulbStatus }); // Send the bulb status as JSON
});

// Start the server
app.listen(PORT, () => {
    console.log(`Server is running on http://192.168.100.37:${PORT}`);
});

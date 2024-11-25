const express = require('express');
const bodyParser = require('body-parser');
const cors = require('cors');
const swaggerJsDoc = require('swagger-jsdoc');
const swaggerUi = require('swagger-ui-express');

const app = express();
const PORT = 8080;

app.use(cors());
app.use(bodyParser.json());

let bulbStatus = false; // Default status: OFF

// Swagger configuration
const swaggerOptions = {
    swaggerDefinition: {
        openapi: '3.0.0',
        info: {
            title: 'Bulb Control API',
            version: '1.0.0',
            description: 'API to control and retrieve the status of a bulb',
        },
        servers: [
            {
                url: `http://192.168.100.37:${PORT}`,
            },
        ],
    },
    apis: ['./index.js'], // Path to the API docs (this file)
};

const swaggerDocs = swaggerJsDoc(swaggerOptions);
app.use('/api-docs', swaggerUi.serve, swaggerUi.setup(swaggerDocs));

/**
 * @swagger
 * /bulb:
 *   post:
 *     summary: Update the bulb status
 *     description: Turn the bulb ON or OFF by sending a JSON payload.
 *     requestBody:
 *       required: true
 *       content:
 *         application/json:
 *           schema:
 *             type: object
 *             properties:
 *               bulbOn:
 *                 type: boolean
 *                 description: True to turn the bulb ON, false to turn it OFF.
 *     responses:
 *       200:
 *         description: Successfully updated the bulb status.
 *         content:
 *           application/json:
 *             schema:
 *               type: object
 *               properties:
 *                 message:
 *                   type: string
 *                   description: Confirmation message.
 *   get:
 *     summary: Retrieve the bulb status
 *     description: Get the current status of the bulb (ON or OFF).
 *     responses:
 *       200:
 *         description: Successfully retrieved the bulb status.
 *         content:
 *           application/json:
 *             schema:
 *               type: object
 *               properties:
 *                 bulbStatus:
 *                   type: boolean
 *                   description: The current bulb status.
 */

// Endpoint to update bulb status via POST
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
    console.log(`Swagger docs available at http://192.168.100.37:${PORT}/api-docs`);
});

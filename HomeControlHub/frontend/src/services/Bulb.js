import React, { useState } from "react";
import axios from "axios";
import { FaLightbulb } from "react-icons/fa";

function Bulb() {
  // State to track bulb on/off
  const [bulbOn, setBulbOn] = useState(false);

  // Function to toggle bulb state
  const toggleBulb = () => {
    const newBulbState = !bulbOn; // Determine new state
    setBulbOn(newBulbState); // Update UI state

    // Send new bulb state to the backend
    axios
      .post("http://192.168.100.37:8080/bulb", { bulbOn: newBulbState })
      .then((response) => {
        console.log("Bulb state sent successfully:", response.data);
      })
      .catch((error) => {
        console.error("Error sending bulb state:", error);
        alert("Failed to update bulb state. Please try again.");
      });
  };

  return (
    <div
      className={`min-h-screen flex items-center justify-center transition-colors duration-500 ${
        bulbOn ? "bg-yellow-200" : "bg-gray-900"
      }`}
    >
      <div className="bg-white shadow-lg rounded-lg p-8 w-96 text-center">
        <h1 className="text-3xl font-bold mb-6 text-gray-800">Bulb Control</h1>

        {/* Bulb Icon and Status */}
        <div className="flex flex-col items-center mb-6">
          <FaLightbulb
            className={`text-7xl ${
              bulbOn ? "text-yellow-500" : "text-gray-400"
            }`}
          />
          <p
            className={`mt-4 text-xl font-medium ${
              bulbOn ? "text-yellow-600" : "text-gray-400"
            }`}
          >
            {bulbOn ? "The Bulb is On" : "The Bulb is Off"}
          </p>
        </div>

        {/* Toggle Button */}
        <button
          onClick={toggleBulb}
          className={`py-3 px-6 rounded-lg text-white text-lg font-medium transition-transform duration-200 ${
            bulbOn
              ? "bg-red-500 hover:bg-red-600"
              : "bg-green-500 hover:bg-green-600"
          }`}
        >
          {bulbOn ? "Turn Off" : "Turn On"}
        </button>
      </div>
    </div>
  );
}

export default Bulb;

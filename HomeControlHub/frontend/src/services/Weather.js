import React, { useEffect, useState } from "react";
import axios from "axios";
import { FaTemperatureHigh, FaWater } from "react-icons/fa";

function App() {
  const [data, setData] = useState({ temperature: "", humidity: "" });
  const [loading, setLoading] = useState(true);

  const fetchData = () => {
    setLoading(true);
    axios
      .get("http://192.168.100.37:8080/weather")
      .then((response) => {
        setData(response.data);
        setLoading(false);
      })
      .catch((error) => {
        console.error("Error fetching data:", error);
        setLoading(false);
      });
  };

  useEffect(() => {
    fetchData();
  }, []);

  return (
    <div className="flex items-center justify-center min-h-screen bg-gradient-to-r from-blue-300 to-green-300">
      <div className="bg-white shadow-lg rounded-lg p-8 w-96">
        <h1 className="text-3xl font-bold text-gray-800 mb-6 text-center">
          Weather Dashboard
        </h1>
        {loading ? (
          <p className="text-gray-500 text-center animate-pulse">Loading...</p>
        ) : (
          <div className="space-y-6">
            {/* Temperature Card */}
            <div className="flex items-center justify-between bg-blue-100 p-4 rounded-lg shadow">
              <div className="flex items-center space-x-3">
                <FaTemperatureHigh className="text-red-500 text-3xl" />
                <div>
                  <h2 className="text-lg font-semibold text-gray-700">
                    Temperature
                  </h2>
                  <p className="text-2xl font-bold text-blue-700">
                    {data.temperature}
                  </p>
                </div>
              </div>
            </div>
            {/* Humidity Card */}
            <div className="flex items-center justify-between bg-green-100 p-4 rounded-lg shadow">
              <div className="flex items-center space-x-3">
                <FaWater className="text-blue-500 text-3xl" />
                <div>
                  <h2 className="text-lg font-semibold text-gray-700">
                    Humidity
                  </h2>
                  <p className="text-2xl font-bold text-green-700">
                    {data.humidity}
                  </p>
                </div>
              </div>
            </div>
          </div>
        )}
        {/* Refresh Button */}
        <button
          onClick={fetchData}
          className="mt-6 w-full bg-gradient-to-r from-blue-500 to-green-500 text-white py-2 px-4 rounded-lg hover:scale-105 transition-transform duration-200"
        >
          Refresh Data
        </button>
      </div>
    </div>
  );
}

export default App;

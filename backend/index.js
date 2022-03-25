import express from "express";
import dotenv from "dotenv";
import cookieParser from "cookie-parser";
import cors from "cors";
import * as mqtt from "mqtt";

import db from "./config/Database.js";
import router from "./routes/index.js";
import Koya from "./models/KoyaModel.js";

const port = 5000;

dotenv.config();
const options = {
  host: "test.mosquitto.org",
  port: 1883,
};
const topicSub = "KoYaApp";
const client = mqtt.connect(options);

// mqtt client and subscribe
client.on("message", async (topic, message) => {
  message = message.toString();
  const ob = JSON.parse(message);
  const temperature = ob.temperature;
  const humidity = ob.humidity;
  const amonia = ob.amonia;

  try {
    await Koya.create({
      temp: temperature,
      hum: humidity,
      amonia: amonia,
      topic: topic,
    });
  } catch (error) {}
});

client.on("connect", () => {
  console.log("Mqtt connected ......");
  client.subscribe(topicSub);
});

client.on("error", () => {
  console.log("error");
});
// end mqtt client

const app = express();

try {
  await db.authenticate();
  console.log("Database connected .......");
  await db.sync();
} catch (error) {
  console.log(error);
}

app.use(cors({ credentials: true }));
app.use(cookieParser());
app.use(express.json());
app.use(router);

app.listen(port, () => {
  console.log(`server running at ${port} .......`);
});

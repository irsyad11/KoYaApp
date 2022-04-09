import express from "express";
import cors from "cors";
import * as mqtt from "mqtt";

import db from "./config/Database.js";
import KalmanAmoniaTesting from "./models/Kf1.js";

const options = {
  host: "test.mosquitto.org",
  port: 1883,
};
const topicKF = "KoyaAppKalmanTest";
const client = mqtt.connect(options);

const app = express();

// mqtt client and subscribe
client.on("message", async (topic, message) => {
  if (topic == topicKF) {
    message = message.toString();
    const ob = JSON.parse(message);
    const Kd1 = ob.Kd1;
    const Kd2 = ob.kd2;
    const Kd3 = ob.Kd3;
    const rd = ob.rd;

    try {
      await KalmanAmoniaTesting.create({
        kd1: Kd1,
        kd2: Kd2,
        kd3: Kd3,
        rd: rd,
        cases: kalmancase,
      });
    } catch (error) {}
  }
});

client.on("connect", () => {
  console.log("Mqtt connected ......");
  client.subscribe(topicKF);
});

client.on("error", () => {
  console.log("error");
});
// end mqtt client

try {
  await db.authenticate();
  console.log("Databse Connected.....");
  await db.sync();
} catch (error) {
  console.log(error);
}
app.use(cors());
app.use(express.json());

app.listen(5000, () => console.log("server running at port 5000"));

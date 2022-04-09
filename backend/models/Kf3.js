import sequelize from "sequelize";
import db from "../config/Database.js";

const { DataTypes } = sequelize;

const KalmanAmoniaTestingHum = db.define(
  "kf_Amonia_testing_hum",
  {
    kd1: {
      type: DataTypes.FLOAT,
    },
    kd2: {
      type: DataTypes.FLOAT,
    },
    kd3: {
      type: DataTypes.FLOAT,
    },
    kd4: {
      type: DataTypes.FLOAT,
    },
    kd5: {
      type: DataTypes.FLOAT,
    },
    rd: {
      type: DataTypes.FLOAT,
    },
  },
  {
    freezeTableName: true,
  }
);

export default KalmanAmoniaTestingHum;

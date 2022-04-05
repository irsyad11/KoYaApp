import sequelize from "sequelize";
import db from "../config/Database.js";

const { DataTypes } = sequelize;

const KoyaSensor = db.define(
  "koya_sensor",
  {
    temp: {
      type: DataTypes.FLOAT,
    },
    hum: {
      type: DataTypes.FLOAT,
    },
    amonia: {
      type: DataTypes.FLOAT,
    },
    id_user: {
      type: DataTypes.INTEGER,
    },
  },
  {
    freezeTableName: true,
  }
);

export default KoyaSensor;

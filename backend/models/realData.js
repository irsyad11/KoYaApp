import sequelize from "sequelize";
import db from "../config/Database.js";

const { DataTypes } = sequelize;

const realDataTesting = db.define(
  "rkf_testing",
  {
    rt: {
      type: DataTypes.FLOAT,
    },
    rh: {
      type: DataTypes.FLOAT,
    },
    ra: {
      type: DataTypes.FLOAT,
    },
    cases: {
      type: DataTypes.INTEGER,
    },
  },
  {
    freezeTableName: true,
  }
);

export default realDataTesting;

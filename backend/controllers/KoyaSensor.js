import KoyaSensor from "../models/KoyaSensorModel.js";

export const getDataSen = async (req, res) => {
  const id = req.query.id;
  try {
    const data = await KoyaSensor.findAll({
      where: {
        id_user: id,
      },
      limit: 1,
      order: [["id", "DESC"]],
    });
    res.json(data);
  } catch (error) {
    console.log(error);
  }
};

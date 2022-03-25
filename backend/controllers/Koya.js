import Koya from "../models/KoyaModel.js";

export const getData = async (req, res) => {
  const topic = req.body.topic;
  try {
    const data = await Koya.findAll({
      limit: 1,
      where: {
        topic: topic,
      },
      order: [["id", "DESC"]],
    });
    res.json(data);
  } catch (error) {
    console.log(error);
  }
};

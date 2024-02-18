// Cette fonction convertit le rang et la couleur en chemin de l'image correspondant

import clubs_2 from '../../Assets/Card\ deck/clubs_2.PNG';
import clubs_3 from '../../Assets/Card\ deck/clubs_3.PNG';
import clubs_4 from '../../Assets/Card\ deck/clubs_4.PNG';
import clubs_5 from '../../Assets/Card\ deck/clubs_5.PNG';
import clubs_6 from '../../Assets/Card\ deck/clubs_6.PNG';
import clubs_7 from '../../Assets/Card\ deck/clubs_7.PNG';
import clubs_8 from '../../Assets/Card\ deck/clubs_8.PNG';
import clubs_9 from '../../Assets/Card\ deck/clubs_9.PNG';
import clubs_10 from '../../Assets/Card\ deck/clubs_10.PNG';
import clubs_ace from '../../Assets/Card\ deck/clubs_ace.PNG';
import clubs_jack from '../../Assets/Card\ deck/clubs_jack.PNG';
import clubs_king from '../../Assets/Card\ deck/clubs_king.PNG';
import clubs_queen from '../../Assets/Card\ deck/clubs_queen.PNG';
import diamonds_2 from '../../Assets/Card\ deck/diamonds_2.PNG';
import diamonds_3 from '../../Assets/Card\ deck/diamonds_3.PNG';
import diamonds_4 from '../../Assets/Card\ deck/diamonds_4.PNG';
import diamonds_5 from '../../Assets/Card\ deck/diamonds_5.PNG';
import diamonds_6 from '../../Assets/Card\ deck/diamonds_6.PNG';
import diamonds_7 from '../../Assets/Card\ deck/diamonds_7.PNG';
import diamonds_8 from '../../Assets/Card\ deck/diamonds_8.PNG';
import diamonds_9 from '../../Assets/Card\ deck/diamonds_9.PNG';
import diamonds_10 from '../../Assets/Card\ deck/diamonds_10.PNG';
import diamonds_ace from '../../Assets/Card\ deck/diamonds_ace.PNG';
import diamonds_jack from '../../Assets/Card\ deck/diamonds_jack.PNG';
import diamonds_king from '../../Assets/Card\ deck/diamonds_king.PNG';
import diamonds_queen from '../../Assets/Card\ deck/diamonds_queen.PNG';
import hearts_2 from '../../Assets/Card\ deck/hearts_2.PNG';
import hearts_3 from '../../Assets/Card\ deck/hearts_3.PNG';
import hearts_4 from '../../Assets/Card\ deck/hearts_4.PNG';
import hearts_5 from '../../Assets/Card\ deck/hearts_5.PNG';
import hearts_6 from '../../Assets/Card\ deck/hearts_6.PNG';
import hearts_7 from '../../Assets/Card\ deck/hearts_7.PNG';
import hearts_8 from '../../Assets/Card\ deck/hearts_8.PNG';
import hearts_9 from '../../Assets/Card\ deck/hearts_9.PNG';
import hearts_10 from '../../Assets/Card\ deck/hearts_10.PNG';
import hearts_ace from '../../Assets/Card\ deck/hearts_ace.PNG';
import hearts_jack from '../../Assets/Card\ deck/hearts_jack.PNG';
import hearts_king from '../../Assets/Card\ deck/hearts_king.PNG';
import hearts_queen from '../../Assets/Card\ deck/hearts_queen.PNG';
import spades_2 from '../../Assets/Card\ deck/spades_2.PNG';
import spades_3 from '../../Assets/Card\ deck/spades_3.PNG';
import spades_4 from '../../Assets/Card\ deck/spades_4.PNG';
import spades_5 from '../../Assets/Card\ deck/spades_5.PNG';
import spades_6 from '../../Assets/Card\ deck/spades_6.PNG';
import spades_7 from '../../Assets/Card\ deck/spades_7.PNG';
import spades_8 from '../../Assets/Card\ deck/spades_8.PNG';
import spades_9 from '../../Assets/Card\ deck/spades_9.PNG';
import spades_10 from '../../Assets/Card\ deck/spades_10.PNG';
import spades_ace from '../../Assets/Card\ deck/spades_ace.PNG';
import spades_jack from '../../Assets/Card\ deck/spades_jack.PNG';
import spades_king from '../../Assets/Card\ deck/spades_king.PNG';
import spades_queen from '../../Assets/Card\ deck/spades_queen.PNG';

const cardImages = {
  'clubs': {
    'two': clubs_2,
    'three': clubs_3,
    'four': clubs_4,
    'five': clubs_5,
    'six': clubs_6,
    'seven': clubs_7,
    'eight': clubs_8,
    'nine': clubs_9,
    'ten': clubs_10,
    'ace': clubs_ace,
    'jack': clubs_jack,
    'queen': clubs_queen,
    'king': clubs_king,
  },
  'diamonds': {
    'two': diamonds_2,
    'three': diamonds_3,
    'four': diamonds_4,
    'five': diamonds_5,
    'six': diamonds_6,
    'seven': diamonds_7,
    'eight': diamonds_8,
    'nine': diamonds_9,
    'ten': diamonds_10,
    'ace': diamonds_ace,
    'jack': diamonds_jack,
    'queen': diamonds_queen,
    'king': diamonds_king,
  },
  'hearts': {
    'two': hearts_2,
    'three': hearts_3,
    'four': hearts_4,
    'five': hearts_5,
    'six': hearts_6,
    'seven': hearts_7,
    'eight': hearts_8,
    'nine': hearts_9,
    'ten': hearts_10,
    'ace': hearts_ace,
    'jack': hearts_jack,
    'queen': hearts_queen,
    'king': hearts_king,
  },
  'spades': {
    'two': spades_2,
    'three': spades_3,
    'four': spades_4,
    'five': spades_5,
    'six': spades_6,
    'seven': spades_7,
    'eight': spades_8,
    'nine': spades_9,
    'ten': spades_10,
    'ace': spades_ace,
    'jack': spades_jack,
    'queen': spades_queen,
    'king': spades_king,
  }
};



const getCardImage = (rank, suit) => {
  // Nous ne nous attendons pas Ã  ce que `rank` ou `suit` soient undefined.
  // Si c'est le cas, nous voulons savoir pourquoi, donc nous vérifions ici.
  if (typeof rank === 'undefined' || typeof suit === 'undefined') {
    console.error('getCardImage was called with undefined rank or suit', { rank, suit });
    return ''; 
  }

  const suitLower = suit.toLowerCase();
  let rankKey = rank.toLowerCase();

  const image = cardImages[suitLower][rankKey];
  if (!image) {
    console.error('No image for this card', { rank, suit });
    return ''; 
  }

  return image;
};

export default getCardImage;
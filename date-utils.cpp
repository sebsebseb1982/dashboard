#include <arduino.h>
#include "date-utils.h"

String DateUtils::translateDayOfTheWeek(int dayOfTheWeek) {
  switch (dayOfTheWeek) {
    case 1:
      return "Dimanche";
      break;

    case 2:
      return "Lundi";
      break;

    case 3:
      return "Mardi";
      break;

    case 4:
      return "Mercredi";
      break;

    case 5:
      return "Jeudi";
      break;

    case 6:
      return "Vendredi";
      break;

    case 7:
      return "Samedi";
      break;

    default:
      return "???";
      break;
  }
}

String DateUtils::translateMonth(int month) {
  switch (month) {
    case 1:
      return "janvier";
      break;

    case 2:
      return "fevrier";
      break;

    case 3:
      return "mars";
      break;

    case 4:
      return "avril";
      break;

    case 5:
      return "mai";
      break;

    case 6:
      return "juin";
      break;

    case 7:
      return "juillet";
      break;

    case 8:
      return "aout";
      break;

    case 9:
      return "septembre";
      break;

    case 10:
      return "octobre";
      break;

    case 11:
      return "novembre";
      break;

    case 12:
      return "decembre";
      break;
    default:
      return "???";
      break;
  }
}
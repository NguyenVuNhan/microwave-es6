#ifndef __REGISTRY_HELPER_H
#define __REGISTRY_HELPER_H

/**
 * @brief sets the LPC clock to the 32 kHz frequency
 */
void setClock(void);

/**
 * @brief configures the LCP so that the ADC can be used
 */
void configureForADC(void);

/**
 * @brief Starts the ADC block
 */
void startAndResetADC(void);

/**
 * @brief Sets the register for the LPC so that the gp_interrupt only triggers on raising edge.
 */
void raisingEdgeSensitivityOn(void);

/**
 * @brief Selects the ADC channel to be used
 */
void selectChannel(unsigned char channel);

/**
 * @brief Start the conversion of the analog to digital value
 */
void startConversion(void);

/**
 * @brief Returns the converted value read from the register
 * @return int 0-255
 */
int getDigitalizedValue(void);

#endif // __REGISTRY_HELPER_H

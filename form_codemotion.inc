<?php

/**
 * @file
 * Simple Form API example.
 */

function form_codemotion_form($form, &$form_state) {
  $form['numbers'] = array(
    '#type' => 'textfield',
    '#title' => t('One Number'),
    '#required' => TRUE,
  );
  $form['alpha'] = array(
    '#type' => 'select',
    '#title' => t('Other value'),
    '#options' => array(
      'web' => t('Web'),
      'hello' => t('Hello'),
      'yep' => t('Yep'),
      'nope' => t('Nope'),
      'what?' => t('What?'),
    ),
  );  
  $form['email'] = array(
    '#type' => 'textfield',
    '#title' => t('E-mail address'),
    '#required' => TRUE,
  );
  $form['random'] = array(
    '#type' => 'textarea',
    '#title' => t('What standardized tests did you take?'),
    '#default_value' => 'Un poco de random?',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit your information'),
  );

  return $form;
}

function form_codemotion_form_validate($form, &$form_state) {
  if(!is_numeric($form_state['values']['numbers'])) {
    form_set_error('numbers', t('Numbers must be a number... genius!'));
  }
if (!valid_email_address($form_state['values']['email'])) {
    form_set_error('email', t('That e-mail address is not valid.'));
  }
}

/**
 * Submit handler for form_example_states_form().
 */
function form_codemotion_form_submit($form, &$form_state) {
  drupal_set_message(t('Submitting values: @values', array('@values' => var_export($form_state['values'], TRUE))));
  $row = array('numbers' => $form_state['values']['numbers'], 'alpha' => $form_state['values']['alpha'], 'random' => $form_state['values']['random']);
  db_insert('codemotion_example')->fields($row)->execute();
  codemotion_mail_send($form_state['values']);
}

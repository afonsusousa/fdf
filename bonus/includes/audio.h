/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:40:00 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/04 21:44:51 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUDIO_H
# define AUDIO_H

# include "types.h"
# include <pthread.h>
# include <stdint.h>

void	init_audio(t_data *data);
void	cleanup_audio(t_data *data);
void	toggle_audio_reactive(t_data *data);
void	process_audio_samples(int16_t *samples, int sample_count, t_data *data);
void	set_point_audio_scale(t_data *data, t_point *point);
int		calculate_audio_bucket_index(t_data *data, t_point *point);

bool	start_pulse_audio(t_data *data);
void	stop_pulse_audio(t_data *data);

#endif
